# 🐶 Alimentador Automático

Alimentador automático para cachorros controlado por ESP32, com agendamento de refeições via RTC DS3231 e acionamento manual por botão.

---

## 📋 Sobre o Projeto

O sistema aciona um motor DC (via relé) em horários pré-definidos para liberar ração automaticamente. Também permite alimentação manual a qualquer momento através de um botão físico. O horário é mantido com precisão pelo módulo RTC DS3231, que continua funcionando mesmo sem energia elétrica.

---

## ⚙️ Funcionalidades

- **Alimentação automática** nos horários de café da manhã (07:00), almoço (13:00) e jantar (19:00)
- **Acionamento manual** via botão físico com debounce por software
- **Motor ativo por 5 segundos** a cada ciclo de alimentação
- **Log serial** com hora atual e estado do botão a cada 5 segundos
- **Sincronização automática** do RTC na primeira inicialização ou após perda de energia

---

## 🛠️ Hardware Necessário

| Componente       | Descrição                              |
|------------------|----------------------------------------|
| ESP32            | Microcontrolador principal             |
| RTC DS3231       | Módulo de relógio de tempo real        |
| Relé             | Acionamento do motor DC                |
| Motor DC         | Mecanismo de liberação de ração        |
| Botão            | Acionamento manual                     |
| Fonte de energia | Alimentação do sistema                 |

---

## 🔌 Mapeamento de Pinos

| Pino ESP32 | Função              |
|------------|---------------------|
| GPIO 15    | Controle do relé    |
| GPIO 23    | Botão (INPUT_PULLUP)|
| GPIO 27    | SDA (RTC DS3231)    |
| GPIO 14    | SCL (RTC DS3231)    |

---

## 📁 Estrutura do Projeto

```
Alimentador-Automatico/
├── src/
│   └── main.cpp        # Código principal
├── platformio.ini      # Configuração da plataforma e bibliotecas
└── README.md
```

---

## 🚀 Como Usar

### Pré-requisitos

- [PlatformIO](https://platformio.org/) instalado (extensão para VS Code recomendada)
- ESP32 conectado via USB

### Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/Giovanni-Cotrim/Alimentador-Automatico.git
   ```

2. Abra a pasta no VS Code com a extensão PlatformIO.

3. As dependências serão instaladas automaticamente conforme o `platformio.ini`.

4. Compile e envie para o ESP32:
   ```bash
   pio run --target upload
   ```

5. Monitore a saída serial (115200 baud) para verificar o funcionamento:
   ```bash
   pio device monitor
   ```

---

## 📦 Dependências

As bibliotecas utilizadas estão declaradas no arquivo `platformio.ini`. A principal é:

- **RTClib** — comunicação com o módulo DS3231 via I2C

---

## 🕐 Lógica de Agendamento

O sistema verifica o horário a cada segundo. Quando `minuto == 0` e `segundo == 0`, checa se a hora atual corresponde a um dos três horários de alimentação:

| Refeição       | Horário |
|----------------|---------|
| Café da manhã  | 07:00   |
| Almoço         | 13:00   |
| Jantar         | 19:00   |

A cada ciclo, o relé é acionado por **5 segundos** para movimentar o motor.