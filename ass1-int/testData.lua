a,b,c = 1,2,3
a,b,c = c,nil,a
print(a)
print(b)
print(c)

list = { 5, 6, 1, 2, 9, 14, 2, 15, 6, 7, 8, 97 }
itemCount=#list
print(itemCount)
itemCount=itemCount - 1
print(itemCount)
repeat
  hasChanged = false
  itemCount=itemCount - 1
  for i = 1, itemCount do
    if list[i] > list[i + 1] then
      print("switch")
      print(list[i])
      print(list[i+1])
      list[i], list[i + 1] = list[i + 1], list[i]
      print(list[i])
      print(list[i+1])
      hasChanged = true
    end
  end
until hasChanged == false
for i = 1,itemCount do
  print (list[i])
end
