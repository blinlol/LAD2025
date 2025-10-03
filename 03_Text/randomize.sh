#!/bin/sh

delay=${1:-0.1}
input=$(cat)
lines=$(printf '%s' "$input" | wc -l)
max_width=0
line_num=0

tmpfile=$(mktemp)
printf '%s\n' "$input" > "$tmpfile"

while IFS= read -r line; do
    len=${#line}
    if [ "$len" -gt "$max_width" ]; then
        max_width=$len
    fi
done < "$tmpfile"

coords_file=$(mktemp)
row=0
while IFS= read -r line; do
    while [ ${#line} -lt "$max_width" ]; do
        line="$line "
    done
    col=0
    while [ $col -lt $max_width ]; do
        char=$(printf '%s' "$line" | cut -c $((col + 1)))
        if [ -z "$char" ]; then
            char=" "
        fi
        printf '%d %d %s\n' "$row" "$col" "$char" >> "$coords_file"
        col=$((col + 1))
    done
    row=$((row + 1))
done < "$tmpfile"

shuffled=$(shuf "$coords_file")

tput sc
clear

printf '%s\n' "$shuffled" | while read -r r c ch; do
    tput cup "$r" "$c"
    printf '%s' "$ch"
    sleep "$delay"
done

tput rc
tput cnorm

rm -f "$tmpfile" "$coords_file"
