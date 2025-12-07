name='张三'
age=11
height=141.5

message='我叫%s,今年%d岁了,我的体重是%s'%(name,age,height)

print(message)
if age>=18:
    print('成年')
else:
    print('未成年')

i=1
while i<10:
    print("i=%d"%i)
    i+=1

news='abc'
for i in news:
    print(i)

for x in range(5):
    print(x)
for x in range(1,5):
    print(x)

#    import time
#    time.sleep(2)

#    from time import *
#   sleep(2)

a_list=[1,2,33,4]

for i in a_list:
    print(i,end=' ')

print('\nnihao{}'.format(age))