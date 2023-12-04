import csv

file_path = 'temp.csv'
entry_count = 0  # 入場カウント
exit_count = 0   # 退出カウント
threshold = 300  # ラインの閾値
threshold_left = 150
threshold_right = 450
direction = None  # 移動方向を保存する変数

with open(file_path, newline='', encoding='utf-8') as csvfile:
    csv_reader = csv.reader(csvfile)

    header = next(csv_reader)
    
    # CSVファイルの各行を処理
    for row in csv_reader:
        label = row[2]  # 物体判別ラベル
        x_coordinate = float(row[0])  # X座標を浮動小数点数として取得
        
        if label == 'person':
            if direction is None:
                if threshold_left < x_coordinate < threshold:
                    direction = 'left'
                elif threshold < x_coordinate < threshold_right:
                    direction = 'right'

            # 一定のラインを越えた場合に入退場を判断
            if direction == 'left' and x_coordinate > threshold:
                entry_count += 1  # ラインを右から左に越えて入場
                direction = 'right'
            elif direction == 'right' and x_coordinate < threshold:
                exit_count += 1   # ラインを左から右に越えて退出
                direction = 'left'
            elif direction == 'left' and x_coordinate < threshold_left:
                direction = None
            elif direction == 'right' and x_coordinate > threshold_right:
                direction = None

print(f'入場数: {entry_count}')
print(f'退出数: {exit_count}')
