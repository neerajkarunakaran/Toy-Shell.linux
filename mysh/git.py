
import subprocess, sys
data = str(sys.argv[1])
subprocess.call(["git", "add", data])
subprocess.call(["git", "commit", "-m", data])
subprocess.call(["git", "push", "origin", "master"])






