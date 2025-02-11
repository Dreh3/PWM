#include <stdio.h> //Biblioteca padrão de C que permite entrada e saída de dados
#include "pico/stdlib.h" //Biblioteca fundamental do SDK
#include "hardware/pwm.h" //Biblioteca para manipular o pwm

#define led_pin 12
#define servo_pin 22

// Conversão de microssegundos para nível de PWM
#define PULSE_TO_LEVEL(pulse) ((pulse) * WRAP_PERIOD / 20000)

//Variáveis para configurar o pwm
#define DIVIDER_PWM 100 //Estabelecendo divisor de clock
#define WRAP_PERIOD 24999 //Com o divisor do clock em 100, o wrap tem valor 24999
#define STEP 5  //Passo de incremento/decremento do duty cycle 
//Com o valor do wrap_period definido, para o ciclo ativo ser 5us o step deve ser 6.5 
//Como o valor precisa ser inteiro, foi atribuído 6, um pouco abaixo 

#define min_pulse 500 //Define valor mínimo do pulso para 0 graus
#define max_pulse 2400 //Define valor máximo do pulso para 180 graus
#define medium_pulse 1470 //Define valor médio do pulso pra 90 graus

uint16_t level = PULSE_TO_LEVEL(min_pulse); //Nível inicial baixo

bool aviso = true; //Controle para exbir mensagem quando estiver em 90 graus
                        //Uma vez que há um intervalo de tolerância, é importante uma variável para controlar a mensagem


void led_config(){
  gpio_init(led_pin);
  gpio_set_dir(led_pin, GPIO_OUT);
  gpio_put(led_pin, 0);
};

//Função para inicializar configurações do pwm
void config_pwm(int pino){  //Função pode ser usada para o led e o servo 
    uint slice;
    gpio_set_function(pino, GPIO_FUNC_PWM); //Configura pino do led como pwm
    slice = pwm_gpio_to_slice_num(pino); //Adiquire o slice do pino
    pwm_set_clkdiv(slice, DIVIDER_PWM); 
    pwm_set_wrap(slice, WRAP_PERIOD);
    pwm_set_gpio_level(pino, level); //Determina com o level desejado
    pwm_set_enabled(slice, true);
};

void mensagem(uint16_t position){
    if(position==PULSE_TO_LEVEL(min_pulse) && aviso){ //Se estiver em 500us emite uma mensagem
        printf("Braço em 0 graus\n");
        aviso = false;
    }else if(position>=PULSE_TO_LEVEL(medium_pulse-10) && position<=PULSE_TO_LEVEL(medium_pulse+10) && aviso==false){ //Se estiver em 1470us emite uma mensagem, com tolerância de +-10
        printf("Braço em 90 graus\n");
        aviso = true;
    }else if(position>=PULSE_TO_LEVEL(max_pulse-10) && position<=PULSE_TO_LEVEL(max_pulse+10) && aviso){ ////Se estiver em 1470us emite outra mensagem
        printf("Braço em 180 graus\n");
        aviso = false;
    };
};

int main()
{
    bool incrementa = true; //Controla se o level vai ser incrementado ou decrementado
    stdio_init_all(); //Inicia comunicação padrão
    config_pwm(servo_pin); //Chama função para configurar pwm no pino do servo
    config_pwm(led_pin); //Chama função para configurar pwm no pino do led

    pwm_set_gpio_level(servo_pin, level); //Coloca braço em 0 graus
    pwm_set_gpio_level(led_pin, level); 
    mensagem(level); //Emite mensagem
    sleep_ms(5000);

    pwm_set_gpio_level(servo_pin, PULSE_TO_LEVEL(medium_pulse)); //Coloca braço em 90 graus
    pwm_set_gpio_level(led_pin, PULSE_TO_LEVEL(medium_pulse)); 
    mensagem(PULSE_TO_LEVEL(medium_pulse)); //Emite mensagem
    sleep_ms(5000);

    pwm_set_gpio_level(servo_pin, PULSE_TO_LEVEL(max_pulse)); //Coloca braço em 180 graus
    pwm_set_gpio_level(led_pin, PULSE_TO_LEVEL(max_pulse));
    mensagem(PULSE_TO_LEVEL(max_pulse)); //Emite mensagem
    sleep_ms(5000);

    while (true) {
        if(incrementa){ //Se incrementa for verdadeira
            level += STEP; //Incrementa level em 5
        }else{           //Se incrmenta for falso
            level -= STEP; //Decrementa level em 5
        };
        //Mudança periódica da posição do braço do servo motor
        pwm_set_gpio_level(servo_pin, level); //Atualiza o level
        pwm_set_gpio_level(led_pin, level);
        mensagem(level); //Emite mensagem
        sleep_ms(10); //Pausa para atualizar e suavizar o movimento
        //Condicional para modificar estado de incremento ou decremento
        if(level>=PULSE_TO_LEVEL(max_pulse) || level<=PULSE_TO_LEVEL(min_pulse)){
            incrementa = !incrementa;
        };
    };
};
