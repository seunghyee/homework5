#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);//행렬의 각 요소를 출력
        }
        printf("\n");//각 행 출력한 후 줄을 바꿈
    }
}
// 동적 메모리 할당을 통해 행렬 생성
int** create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}
//행렬을 랜덤한 값으로 채우는 함수
void fill_matrix(int **matrix, int rows, int cols, int seed) {
    srand(time(0) + seed);//랜덤 시드 생성
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;//0부터 99까지의 랜덤한 값으로 채움
        }
    }
}
//두 행렬의 각 요소를 더하여 새로운 행렬 생성
int** add_matrix(int **A, int **B, int rows, int cols) {
    int **result = create_matrix(rows, cols);//결과 저장할 새로운 행렬 생성
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];//A와 B의 각 요소를 더함
        }
    }
    return result;
}
//두 행렬의 각 요소를 빼서 새로운 행렬 생성
int** subtract_matrix(int **A, int **B, int rows, int cols) {
    int **result = create_matrix(rows, cols);//결과를 저장할 새로운 행렬 생성
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];//A와 B의 각 요소를 뺌
        }
    }
    return result;
}
//행렬의 전치를 수행하여 새로운 행렬 생성
int** transpose_matrix(int **A, int rows, int cols) {
    int **result = create_matrix(cols, rows);//결과를 저장할 새로운 행렬 생성
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = A[i][j];//A의 요소를 전치하여 결과행렬에 저장
        }
    }
    return result;
}
//두 행렬의 곱셈을 수행하여 새로운 행렬 생성
int** multiply_matrix(int **A, int **B, int rowsA, int colsA, int rowsB, int colsB) {
    if (colsA != rowsB) {
        printf("오류: 행렬의 차원이 곱셈에 적합하지 않습니다. \n");
        return NULL;//행렬의 차원이 곱셈에 적합하지 않으면 NULL 반환
    }
    int **result = create_matrix(rowsA, colsB);//결과를 저장할 새로운 행렬 생성
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;//결과 행렬의 각 요소를 0으로 초기화
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];//A와 B의 곱셈을 계산하여 결과행렬에 더함
            }
        }
    }
    return result;
}
//동적으로 할당된 메모리를 해제하는 함수
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);//각 행의 메모리를 해제
    }
    free(matrix);//행렬의 포인터 배열의 메모리를 해제
}

int main() {
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);//사용자로부터 행과 열의 개수 입력받음

    int **A = create_matrix(rows, cols);//행렬 A를 동적으로 할당
    fill_matrix(A, rows, cols, 1);//랜덤 값으로 행렬 A 채움
    print_matrix(A, rows, cols);// 행렬 A 출력
    printf("[----- [son seunghye] [2023078010] -----]\n");
    int **B = create_matrix(rows, cols);//행렬 B를 동적으로 할당
    fill_matrix(B, rows, cols, 2);//랜덤 값으로 행렬 B 채움
    print_matrix(B, rows, cols);//행렬 B 출력
    printf("--------------------\n");
    int **add_result = add_matrix(A, B, rows, cols);//A와 B의 덧셈 결과 저장
    print_matrix(add_result, rows, cols);//A와 B 덧셈 결과 출력
    printf("--------------------\n");
    int **subtract_result = subtract_matrix(A, B, rows, cols);//A와 B 뺄셈 결과 저장
    print_matrix(subtract_result, rows, cols);//A와 B 뺄셈 결과 출력
    printf("--------------------\n");
    int **transpose_result = transpose_matrix(A, rows, cols);//A의 전치행렬 계산하여 저장
    print_matrix(transpose_result, cols, rows);//A의 전치행렬 출력
    printf("--------------------\n");
    int **multiply_result = multiply_matrix(A, B, rows, cols, rows, cols);//A와 B의 곱셈 결과 저장
    if (multiply_result != NULL) {// 곱셈 가능한 경우에만 출력
        print_matrix(multiply_result, rows, cols);//A와B 곱셈 결과 출력
    }
    printf("--------------------\n");
    //할당된 메모리 해제
    free_matrix(A, rows);
    free_matrix(B, rows);
    free_matrix(add_result, rows);
    free_matrix(subtract_result, rows);
    free_matrix(transpose_result, cols);
    if (multiply_result != NULL) {
        free_matrix(multiply_result, rows);
    }

    return 0;
}
