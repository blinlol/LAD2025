file ./range

set $iteration = 0

b main.c:18 if ((++$iteration >= 28) && ($iteration < 36))

commands 1
printf "@@@ %d ", from
printf "%d ", to
printf "%d ", step
printf "%d\n", i
c
end

run -100 100 3 > /dev/null
q
