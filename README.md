# PWM

__Tarefa - Aula Síncrona 06/02__<br>
Repositório criado com o intuito de realizar a Tarefa da aula Síncrona do dia 06 de fevereiro de 2025 sobre PWM.

__Responsável pelo desenvolvimento:__
Andressa Sousa Fonseca

## Descrição Da Tarefa 
__Aplicação de PWM para manipular servomotor e led RGB__  <br>

__Os Componentes necessários para a execução da atividade são:__

1) Microcontrolador Raspberry Pi Pico W.
2) Servomotor – motor micro servo padrão – Wokwi. 
3) Led RGB no pino 12 - Placa.

__As funcionalidade básicas especificadas para a atividade são:__

1) Considerando a GPIO 22, defina a sua frequência de PWM para, aproximadamente, 50Hz – período de 20ms. 
2) Defina o ciclo ativo do módulo PWM para 2.400µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,12%. istoajustará a flange (braço) do servomotor para a posição de, aproximadamente, 180 graus. Aguarde 05 segundos nesta posição. 
3) Defina o ciclo ativo do módulo PWM para 1.470µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,0735%. Isto ajustará a flange do servomotor para a posição de, aproximadamente, 90 graus. Aguarde 05 segundos nesta posição. 
4) Defina o ciclo ativo do módulo PWM para 500µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%.
5) Defina o ciclo ativo do módulo PWM para 500µs (microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%.Isto ajustará a flange do servomotor para a posição de, aproximadamente, 0 graus. Aguarde 05 segundos nesta posição.
5) Após a realização das proposições anteriores, crie uma rotina para movimentação periódica do braço do servomotor entre os ângulos de 0 e 180 graus. Obs.: a movimentação da flange deve ser suave, recomenda-se o incremento de ciclo ativo de ±5µs, com um atraso de ajuste de 10ms.
6) Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIO 12.


__Uma breve explicação do desenvolvimento e resultados obtidos podem ser vistos no vídeo endereçado no seguinte link: [Aplicações de PWM]().__

__O projeto no simulador Wokwi Web pode ser acessado no seguinte link: [PWM_](https://wokwi.com/projects/422560201223537665).__

## Detalhamento Do Projeto

### 1. Explicação do funcionamento

#### Simulador Wokwi - Comportamento do Braço do Servomotor

O projeto utilizasse do controle de pwm para manipular o movimento do braço de um servomotor em 0°, 90° e 180°. Inicialmente, o braço permanece cinco segundos em cada uma das posições iniciais. E após isso, movesse entre 0 e 180 periodicamente com um clico ativo de aproximadamente 5us. Ademais, mensagens são mostradas para indicar a posição atual do braço. 
O valores definidos para a configuração do PWM são: 
<div align="center">
  <img src="https://github.com/user-attachments/assets/e2c5c290-4717-4f52-8143-30f35431bf90" alt="valores pwm" width="900"/>
</div>

#### Comportamento do Led

Os valores e configurações de PWM são as mesmos mencionados acima. Com uso do PWM, é possível perceber que o led aumenta e dimunui o brilho constantemente de maneira suave. 

### 2. Observações

O simulador Integrado Wokwi permite visualizar o giro do braço do servomotor e o led. Na placa, é possível observar apenas o comportamento do led.
