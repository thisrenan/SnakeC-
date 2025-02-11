FROM ubuntu:latest

# Instalar dependências
RUN apt-get update && \
    apt-get install -y g++ cmake make build-essential && \
    rm -rf /var/lib/apt/lists/*

# Criar diretório de trabalho
WORKDIR /app

# Copiar código-fonte para o contêiner
COPY . /app

# Criar diretório para build
RUN mkdir build
WORKDIR /app/build

# Compilar aplicação
RUN cmake .. && make

# Definir comando de execução
CMD ["./app"]