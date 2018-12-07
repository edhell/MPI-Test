# MPI-Test
Multiplicação matrizes de dimensão n x n
* Em todos computadores envolvimentos o executavel deve estar no mesmo local de diretório, por exemplo: "c:\mpi"
* Instalado: 
  1. Download/Install HPC Pack 2012 Client. http://www.microsoft.com/en-us/download/confirmation.aspx?id=36044
  2. Download/Install HPC Pack 2012 MS-MPI. http://www.microsoft.com/en-us/download/confirmation.aspx?id=36045
  3. Copiar pasta "Bin" de "C:\Program Files\Microsoft MPI" e colar em: "C:\Program Files\Microsoft HPC Pack 2012"
  4. Em caso de erro na execução, adicionar computadores ao arquivo hosts
  
  
Comandos 
* SLAVES (Windows): "smpd –d 3"
* MASTER (Windows): "mpiexec.exe –d 3 –hosts 2 192.168.25.2 4 192.168.25.10 4 .\Project1.exe 1000"

  * "-d 3": DEGUB mostrando tudo
  * "-hosts 2": 2 hosts serão utilizados
  * "192.168.25.2 4 ": 4 Processos no host 192.168.25.2
  * "Project1.exe 1000": Aplicativo que será executado, criando matrizes de dimensão 1000*1000

Qualquer dúvida entre em contato: www.edinfo.com.br
