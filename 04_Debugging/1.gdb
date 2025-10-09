file ./range
break main.c:18 if (i%5==0)
commands 1
printf "@@@ %d ", from
printf "%d ", to
printf "%d ", step
printf "%d\n", i
c
end
run 1 12 > /dev/null
q
