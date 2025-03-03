#!/bin/bash
# 測試案例
cases=(
    "80000 80"   # Case A
    "800 8000"   # Case B
    "8 800000"   # Case C
)

# 迴圈執行每個案例
for case in "${cases[@]}"; do
    read N M <<< "$case"
    echo "========================================"
    echo "Running test case: N=$N, M=$M"
    
    time ./program $N $M 1
    time ./program $N $M 4
    
    # # 顯示結果
    # echo "T1 (1 thread): $T1 seconds"
    # echo "T4 (4 threads): $T4 seconds"
    
    # # 計算加速比
    # SPEEDUP=$(echo "scale=2; $(echo $T1 | sed 's/m/*60+/') / $(echo $T4 | sed 's/m/*60+/')" | bc)
    # echo "Speedup (T1 / T4): $SPEEDUP"
done

echo "========================================"
echo "
