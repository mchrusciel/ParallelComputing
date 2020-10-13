n = 32
p = 6

seriesList = []

for i in range(p):
    my_last = i * (n/p) + n/p + (n%p)*((p-i)/p)
   

    my_first = my_last - (i *(n/p)  + (n%p)*((p-i)/p))
    seriesList.append(int(my_first))
    seriesList.append(int(my_last))
    

print(seriesList)