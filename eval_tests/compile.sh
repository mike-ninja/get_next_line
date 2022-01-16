gcc main.c ../get_next_line.c -L. -lft -o test_gnl
time leaks -atExit -- ./test_gnl bible.txt