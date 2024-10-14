se nu rnu bs=2 sw=4 ts=4 hls ls=2 si acd bo=all mouse=a

:inoremap " ""<Esc>i
:inoremap {<CR> {<CR>}<Esc>ko
:inoremap {{ {}<ESC>i

map <F9> :w<bar>!g++ "%" -o %:r -std=c++17 -Wall -Wextra -Wshadow -O2 -DLOCAL -g -fsanitize=undefined,address<CR>
map <F8> :!./%:r<CR>

ca hash w !cpp -dD -P -fpreprocessed \| tr -d "[:space:]" \| md5sum \| cut -c-6