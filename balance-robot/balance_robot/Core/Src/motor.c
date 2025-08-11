#include "motor.h"

// 전역 변수로 현재 속도 저장 (freertos.c에서 extern으로 선언)
extern volatile uint16_t speedVal;

void stopHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

    // PWM도 정지
    TIM2->CCR1 = 0;
    TIM2->CCR2 = 0;
}

void wHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

    // 양쪽 모터 같은 속도로 설정
    TIM2->CCR1 = speedVal;
    TIM2->CCR2 = speedVal;
}

void sHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

    // 양쪽 모터 같은 속도로 설정
    TIM2->CCR1 = speedVal;
    TIM2->CCR2 = speedVal;
}

void aHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); // 왼쪽 모터 정지
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);   // 오른쪽 모터 전진
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // 왼쪽 모터 정지

    // 좌회전: 왼쪽 모터 정지, 오른쪽 모터만 동작
    TIM2->CCR1 = 0;
    TIM2->CCR2 = speedVal;
}

void dHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // 오른쪽 모터 정지
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // 왼쪽 모터 전진

    // 우회전: 오른쪽 모터 정지, 왼쪽 모터만 동작
    TIM2->CCR1 = speedVal;
    TIM2->CCR2 = 0;
}

// 전진 + 좌회전 (부드러운 커브)
void wlHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

    // 좌회전: 왼쪽 모터 느리게, 오른쪽 모터 빠르게
    TIM2->CCR1 = speedVal / 4;  // 왼쪽 모터 절반 속도
    TIM2->CCR2 = speedVal;      // 오른쪽 모터 풀 속도
}

// 전진 + 우회전 (부드러운 커브)
void wrHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

    // 우회전: 오른쪽 모터 느리게, 왼쪽 모터 빠르게
    TIM2->CCR1 = speedVal;      // 왼쪽 모터 풀 속도
    TIM2->CCR2 = speedVal / 4;  // 오른쪽 모터 절반 속도
}

// 후진 + 좌회전
void slHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

    // 후진 중 좌회전: 왼쪽 모터 느리게, 오른쪽 모터 빠르게
    TIM2->CCR1 = speedVal / 4;  // 왼쪽 모터 절반 속도
    TIM2->CCR2 = speedVal;      // 오른쪽 모터 풀 속도
}

// 후진 + 우회전
void srHandler()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

    // 후진 중 우회전: 오른쪽 모터 느리게, 왼쪽 모터 빠르게
    TIM2->CCR1 = speedVal;      // 왼쪽 모터 풀 속도
    TIM2->CCR2 = speedVal / 4;  // 오른쪽 모터 절반 속도
}

void speedInit()
{
    TIM2->CCR1 = speedVal;
    TIM2->CCR2 = speedVal;
}
