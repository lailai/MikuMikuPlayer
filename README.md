MikuMikuPlayer
==============
説明
----
MikuMikuDance で使用される PMD ファイルと VMD ファイルを読み込み Android 端末で描画することを目標とします。
描画には OpenGL for Embedded Systems (OpenGL ES) 2.0 を使用します。
アプリケーションの構成は、 GLSurfaceView でサーフェスを作成し、描画処理は NDK に投げます。
NDK は、 v9 辺りを使用して開発を進めていきますが、気が変わるかもしれません。
現在は、最小の構成 (glClearColor 関数で背景色を指定し、 glClear 関数で背景色の塗りつぶし) です。