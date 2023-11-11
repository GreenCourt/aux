#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

struct Process {
  string so, se;
  int return_code = -1;
  bool time_limit_exceeded = false;

  Process(const vector<string>& args, const string& input, int timeout=0) {
    constexpr int R = 0, W = 1;
    int pipe_stdin[2], pipe_stdout[2], pipe_stderr[2];

    assert(pipe(pipe_stdin) == 0);
    assert(pipe(pipe_stdout) == 0);
    assert(pipe(pipe_stderr) == 0);

    pid_t pid = fork();
    assert(pid >= 0);

    if(pid == 0) { // child process
      assert(close(pipe_stdin[W]) == 0);
      assert(close(pipe_stdout[R]) == 0);
      assert(close(pipe_stderr[R]) == 0);
      assert(dup2(pipe_stdin[R], STDIN_FILENO) != -1);
      assert(dup2(pipe_stdout[W], STDOUT_FILENO) != -1);
      assert(dup2(pipe_stderr[W], STDERR_FILENO) != -1);
      assert(close(pipe_stdin[R]) == 0);
      assert(close(pipe_stdout[W]) == 0);
      assert(close(pipe_stderr[W]) == 0);

      vector<char*> c_args;
      for(string const &i : args) c_args.push_back(const_cast<char*>(i.c_str()));
      c_args.push_back(nullptr);
      assert(execvp(c_args[0], c_args.data()));
    }
    else {
      auto wait_child = [&]() {
        assert(close(pipe_stdin[R]) == 0);
        assert(close(pipe_stdout[W]) == 0);
        assert(close(pipe_stderr[W]) == 0);

        thread th_out(read_pipe, pipe_stdout[R], ref(so));
        thread th_err(read_pipe, pipe_stderr[R], ref(se));

        if(!input.empty()) write_pipe(pipe_stdin[W], input);
        assert(close(pipe_stdin[W]) == 0);

        th_out.join();
        th_err.join();

        assert(close(pipe_stdout[R]) == 0);
        assert(close(pipe_stderr[R]) == 0);

        int status;
        assert(wait(&status) != -1);
        return_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
      };

      if(timeout) {
        auto a = async(wait_child);
        if (a.wait_for(chrono::seconds(timeout)) == future_status::timeout) {
          kill(pid, SIGKILL);
          time_limit_exceeded = true;
        }
      }
      else {
        wait_child();
      }
    }
  }
  private:
  static void write_pipe(int fd, const string &text) {
    const char* buf = text.c_str();
    int sz = text.size();
    for(int p = 0; p < sz; ) {
      int bytes = write(fd, buf+p, min(sz - p, 1024));
      assert(bytes != -1);
      p += bytes;
    }
  }
  static void read_pipe(int fd, string &text) {
    char buf[1024];
    int bytes;
    stringstream ss;
    while(true) {
      bytes = read(fd, buf, sizeof(buf));
      assert(bytes != -1);
      if(bytes == 0) break;
      ss << string(buf, bytes);
    }
    text = ss.str();
  }
};
