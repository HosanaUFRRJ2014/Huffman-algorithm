# Huffman-algorithm

Arquivos código-fonte:  (os códigos do programa)

- heap.h
- arvore.h
- huffman.h

Arquivos exemplo: (para usar para a compactação)

- tol.txt
- winter.txt
- journey.txt
- fundation.txt
- guide.txt

*Recomendo usar esses arquivos como exemplo porque já tirei qualquer caractere fora da tabela ASCII que possa dar algum erro de execução.*

Quando ocorrer a descompactação, os arquivos serão nomeados da seguite maneira. Exemplo:
o arquivo tol.txt será compactado e, ao ser decompactado, o conteúdo será armazenado num arquivo tol2.txt.
Fiz assim porque , se tivesse o mesmo nome, sobreescreveria o arquivo original, que se encontra na mesma pasta para facilitar os testes.

### Comando para compilar:

    gcc huffman.c -o huf


### Comandos para executar:

- A compressão:
 
        ./huf <arquivoAcompactar>.txt <arquivoCompactado>.huf
        
- A descompressão:
        
        ./huf <arquivoCompactado>.huf

  - **arquivoAcompactar** é um dos textos exemplo.
  - **arquivoCompactado** é o nome, que deverá ser fornecido pelo usuário, do arquivo-saída para os dados compactados. Na fase da descompressão, deve ser fornecido um <arquivo>.huf existente, criado na fase de compressão.
