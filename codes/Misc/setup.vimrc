se nu rnu bs=2 sw=4 ts=4 hls ls=2 si acd bo=all mouse=a

:inoremap " ""<Esc>i
:inoremap {<CR> {<CR>}<Esc>ko
:inoremap {{ {}<ESC>i

function! F(...)
	execute '!./%:r < ./' . a:1
endfunction
command! -nargs=* R call F(<f-args>)

map <F7> :w<bar>!g++ "%" -o %:r -std=c++17 -Wall -Wextra -Wshadow -O2 -DLOCAL -g -fsanitize=undefined,address<CR>
map <F8> :!./%:r<CR>
map <F9> :!./%:r < ./%:r.in<CR>

ca hash w !cpp -dD -P -fpreprocessed \| tr -d "[:space:]" \| md5sum \| cut -c-6

" i+<esc>25A---+<esc>
" o|<esc>25A   |<esc>
" "ggVGyG35pGdd
