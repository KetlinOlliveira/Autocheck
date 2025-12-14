# Projeto Autocheck 

Este repositório apresenta um sistema completo de gestão para o controle de manutenções de veículos. Desenvolvido em Linguagem C, o projeto tem como foco a aplicação de estruturas de dados dinâmicas e técnicas avançadas de gerenciamento de memória, sendo uma excelente vitrine para o desenvolvimento de sistemas complexos em C.

#### **`💡 Funcionalidades do Sistema`**

O sistema foi projetado para gerenciar o ciclo de vida da manutenção, incluindo:

Cadastro de Veículos: Registro de informações detalhadas do veículo (modelo, ano, placa, etc.).

Registro de Serviços: Inclusão e acompanhamento de serviços de manutenção realizados em cada veículo.

Consulta e Relatórios: Funcionalidades de busca para listar veículos, histórico de manutenção e status de serviços.

Remoção Segura: Procedimentos para remover veículos ou registros de manutenção, garantindo a liberação correta da memória.

#### **`💻 Estrutura Técnica e Implementação Avançada em C`**

Este projeto se destaca pela sua arquitetura baseada em princípios robustos de C:

Listas Encadeadas (Linked Lists): O núcleo do sistema é construído sobre listas encadeadas. Essa estrutura dinâmica é usada para gerenciar coleções de veículos e seus serviços, permitindo que o sistema cresça e encolha conforme necessário, sem limites de tamanho pré-definidos.

Alocação Dinâmica de Memória (malloc / free): Utilização intensiva de alocação dinâmica para criar nós nas listas encadeadas, garantindo o uso eficiente da memória e prevenindo memory leaks (vazamentos de memória).

Modularização: O código é estritamente modular, separado por responsabilidade em diferentes arquivos (veiculo.c, servico.c, manutencao.c, etc.), promovendo organização, reutilização de código e facilidade de manutenção.

Persistência de Dados (Arquivos): Os dados são armazenados e recuperados de forma persistente através de manipulação de arquivos, garantindo que as informações do sistema permaneçam intactas após o encerramento do programa.
