// harmony parameters 
#define ITERATION 100000   // ITERATION
#define IND_SIZE  100    // HMのサイズ
#define R_A       0.8    // 選択比率
#define R_P       0.3    // 値調整比率
#define BANDWIDTH 0.1    // バンド幅
#define XMAX      1.0

// individual of harmony(NC)
typedef struct{ 
    float whid[I_MAX][J_MAX]; 
    float wout[J_MAX][K_MAX]; 
    float E;
}INDIVIDUAL;