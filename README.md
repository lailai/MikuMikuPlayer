MikuMikuPlayer
==============
説明
----
MikuMikuDance で使用される PMD ファイルと VMD ファイルを読み込み Android 端末で描画することを目標とします。
描画には OpenGL for Embedded Systems (OpenGL ES) 2.0 を使用します。
アプリケーションの構成は、 GLSurfaceView でサーフェスを作成し、描画処理は NDK に投げます。
NDK は、 v9 辺りを使用して開発を進めていきますが、気が変わるかもしれません。

構成
----
動作に必要なファイルの構成
* /sdcard/MMD/creeper_512x512.bmp
* /sdcard/MMD/pmd/Normal.pmd
    * PMD ファイル内で必要とされるファイルセット

読み込み可能な画像ファイル
* BMP (24ビットビットマップ)

動作
----
* /sdcard/MMD/creeper_512x512.bmp を読み込み奥のほうに描画
* /sdcard/MMD/pmd/Normal.pmd を読み込みそのまま描画

スクリーンショット
------------------
![Screenshot][ss]

[ss]: https://github.com/lailai/MikuMikuPlayer/blob/master/screenshot.jpg?raw=true "Screenshot"
