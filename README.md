MikuMikuPlayer
==============
説明
----
MikuMikuDance で使用される PMD ファイルと VMD ファイルを読み込み Android 端末で描画することを目標とします。
描画には OpenGL for Embedded Systems (OpenGL ES) 2.0 を使用します。
アプリケーションの構成は、 GLSurfaceView でサーフェスを作成し、描画処理は NDK に投げます。
NDK は、 v9 辺りを使用して開発を進めていきますが、気が変わるかもしれません。
現在は、三角形のポリゴンを2枚合わせて四角形を作成し、そこに適当なテクスチャを貼り付けています。
取得する画像ファイルは /sdcard/MMD/creeper_512x512.bmp です。
ファイル名は固定で、そこに24ビットの BMP 形式のファイルを配置すれば実行時に描画されます。
