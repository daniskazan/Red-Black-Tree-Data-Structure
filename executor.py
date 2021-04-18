import subprocess
from subprocess import PIPE


def run_cpp_thing(path_to_data):
    process = subprocess.run(f'cmd /c a.exe < {path_to_data}',
                shell=True,
                stdout=PIPE,
                stderr=PIPE,
                timeout=100000)
    print(len(process.stdout))
    stdout_text = (process.stdout.decode("utf-8"))
    print(process.returncode)
    return stdout_text

n = input()

print(run_cpp_thing(n))
