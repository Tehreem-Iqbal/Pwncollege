from pwn import *
import subprocess

p1 = subprocess.Popen(["/bin/cat"], stdin= subprocess.PIPE, stdout=subprocess.PIPE )
p2 = subprocess.Popen(["./a.out"], stdin=p1.stdout, stdout=subprocess.PIPE)
p3 = subprocess.Popen(["/bin/cat"], stdin=p2.stdout, stdout=subprocess.PIPE)

for i in range(31):
  line = p3.stdout.readline()
  print(line)


for i in range(50):
  line = str(p3.stdout.readline())
  print(line)
  print(i,"=========================")
  lane1 = line[line.find(':')+2:-3]
  print(lane1)
  print("=========================")
  sol = eval(lane1)
  print(sol)
  sol = str(sol)+'\n'
  p1.stdin.write(bytes(sol,'utf-8'))
  p1.stdin.flush()
  #r, e = p1.communicate(bytes(sol,'utf-8'))
  #print(r,e,"=========================")
  print(p3.stdout.readline())

print(p3.stdout.readline())
print(p3.stdout.readline())
print(p3.stdout.readline())

p1.wait()
p2.wait()
p3.wait()


'''
line = str(p3.stdout.readline())
print(line)
print("=========================")
lane1 = line[line.find(':')+2:-3]
print(lane1)
print("=========================")
sol = eval(lane1)
print(sol)
sol = str(sol)+'\n'
#p1.stdin.write(bytes(sol,'utf-8'))
p1.communicate(bytes(sol,'utf-8'))
print("=========================")
print(p3.stdout.readline())
print(p3.stdout.readline())
'''


