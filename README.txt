#Dependências

- API GraphViewer, fornecida nas aulas, para visualização de grafos.

#Input files

Os ficheiros com informações relativas ao contexto do problema encontram-se na pasta 'data' dos respetivos mapas (maps/GridGraphs/custom/8x8/data e maps/PortoMap/data).

#Instruções de compilação
Para compilar o projeto é necessária uma instalação CLion ou cmake.

CLion: Importar o projeto e executar com as ferramentas do programa.

CLI: Correr o seguinte comando a partir da raiz do projeto para compilar

cmake -S ./ -B ./build && cd ./build && make

Executar a partir da pasta ./build com:

./Proj

É necessário executar o projeto numa pasta um nível abaixo da pasta de raíz.
