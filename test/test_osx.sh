#!/bin/bash

# Sets the bin of ft_ls path and tmp file path according to PWD
if [[ $PWD == */test ]]; then
  FT_LS_BIN=../ft_ls
else
  FT_LS_BIN=./ft_ls
fi

#
# Here are the tests
#
#$FT_LS_BIN -l
#$FT_LS_BIN -l ""
#$FT_LS_BIN -l "zgzr/zefzerg"
#$FT_LS_BIN -l "/usr/zefzerg"

#mkdir -p  "folder/.cache/noncache1/coucou"
#mkdir -p  "folder/.cache/noncache2"
#$FT_LS_BIN -lR "folder"
#rm -rf folder

#$FT_LS_BIN -lR "/usr/bin"
#$FT_LS_BIN -lR "$HOME"

#mkdir folder
#touch folder/update.time
#touch fodler/update-one.time
#$FT_LS_BIN -l folder
#rm -rf folder

#$FT_LS_BIN -lR /cores

#FT_LS_BIN .. Makefile

# touch aaaaa bbbbbb cccccc dddddd eeeeeee fffffff gggggg hhhhhh iiiiii jjjjj kkkkk lllll mmmmm nnnnn eeeee ssssss ttttt uuuuuu \
# vvvvv wwwww xxxxx yyyyy zzzzz 11111 222222 3333333 444444 555555 666666 777777 88888 9999 10001010101

# FT_LS_BIN aaaaa bbbbbb cccccc dddddd eeeeeee fffffff gggggg hhhhhh iiiiii jjjjj kkkkk lllll mmmmm nnnnn eeeee ssssss ttttt uuuuuu \
# vvvvv wwwww xxxxx yyyyy zzzzz 11111 222222 3333333 444444 555555 666666 777777 88888 9999 10001010101

# rm aaaaa bbbbbb cccccc dddddd eeeeeee fffffff gggggg hhhhhh iiiiii jjjjj kkkkk lllll mmmmm nnnnn eeeee ssssss ttttt uuuuuu \
# vvvvv wwwww xxxxx yyyyy zzzzz 11111 222222 3333333 444444 555555 666666 777777 88888 9999 10001010101

# touch "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
#        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
#        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
# ln -s a "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
#        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
#        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
# ./ft_ls -l .
# ./ft_ls -l a
# ./ft_ls -li a
# ./ft_ls -lt a
