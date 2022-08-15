# File compactor with Huffman algorithm

## Instruções
 - Todos os arquivos .h estão dentro do diretório "include".
 - Todas as implementações dos arquivos .h estão no diretório "src".
 - O diretório "objects" será criado temporariamente toda vez que compilarmos o programa.
 - Os arquivos executáveis estarã no diretório raíz.

 ## Comandos
 - "make" -> compilar os arquivos
 - "make clean" -> remover os arquivos temporários.
 - "make zip f=nome_do_arquivo.extensão" -> compactar um arquivo.
 - "make unzip f=nome_do_arquivo.comp" -> descompactar um arquivo.
 - "make valgrindz f=nome_do_arquivo.extensão" -> passar o valgrind sobre o programa de compactação.
 - "make valgrindu f=nome_do_arquivo.comp" -> passar o valgrind sobre o programa de descompactação.
 - "make size f=nome_do_arquivo" -> Este comando só funciona para arquivos .txt. Sua função é informar o tamanho do arquivo original e do arquivo compactado para fins de comparação.

 ## Observações
 - Qualquer arquivo binário pode ser inserido na entrada do programa de compactação, porém as taxas de compactação são superiores em arquivos .txt.
 - O programa é ideal para compactar arquivos .txt acima de 1kB.
