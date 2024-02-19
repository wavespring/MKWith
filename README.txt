１．初めに
　このソースコードはDCON2024向け空港リムジンバス乗車数検知システムである。

２．必要な機材
　このソースコードの実行には以下の製品が必要である。
　・M5Stack UnitV2 AIカメラ
　・M5Stack ATOM Motionキット（M5Stack ATOM Lite内蔵）
　・M5Stack用超音波測距ユニットI/O
　・Pythonプログラムを実行可能なPC
　また、上記製品に必要な充電器や接続ケーブルが別途必要である。

３．プログラムの構成
　同梱するプログラムは以下の用途となっている。
　・controller.ino→ATOM Liteに書き込み、UnitV2や冷却ファン、PCとの通信を行う
　・save.py→PCで実行し、ATOM Liteから送られてきた人数データを保存する
　・detection.py→PCで実行し、人数をカウントする
