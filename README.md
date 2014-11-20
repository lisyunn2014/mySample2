mySample2
=========

cocos2dx-3.x Android obb expansion sample 

豪华版飞机大战源码，开发环境cocos2d-x3.2alpha
https://codeload.github.com
よりの改良

cocos2dx-3.x Android obb expansion sample v1.1

cocos2dx-3.x系にAndroid obb 拡張ファイルの使用サンプルプロジェクトになります。

cocos2d-x3.2alphaのサンプルプロジェクトPlaneを使用

▪️必要なライブラリー

android-sdk/sdk/extras/google/play_apk_expansion_zip_file

▪️修正したファイル コメント：obb expansionで検索可

1:mySample2/obb-expansion-cocos2dx3.2/cocos2d/cocos/platform/android/java/src/org/cocos2dx/lib/Cocos2dxHelper.java

2:mySample2/obb-expansion-cocos2dx3.2/cocos2d/cocos/platform/android/java/src/org/cocos2dx/lib/Cocos2dxMusic.java

3:mySample2/obb-expansion-cocos2dx3.2/cocos2d/cocos/platform/android/java/src/org/cocos2dx/lib/Cocos2dxSound.java

4:mySample2/obb-expansion-cocos2dx3.2/cocos2d/cocos/platform/android/CCFileUtilsAndroid.cpp

▪️手順

1:mySample2/obb-expansion-cocos2dx3.2/assets/ 作成

2:mySample2/obb-expansion-cocos2dx3.2/Resources/* Resources下のフォルダおよびファイルを
上記1:assets下にコピー、そして、Resources下に空する

3:mac termianlで

a: $cd mySample2/obb-expansion-cocos2dx3.2/

b: $ zip -rn .ogg:.mp3:.wav assets.zip assets/

c: $ mv assets.zip main.2.com.superman.plane.obb

d: $ mkdir com.superman.plane

e: $ mv main.2.com.superman.plane.obb com.superman.plane/

4:上記3で作成したcom.superman.planeをAndroid デバイスにコピー
僕の場合、eclipse DDMS File ExplorerでAndroid AQUOS PHONE SHARP SHL21の/storage/sdcard0/Android/obb/に入れる
/storage/sdcard0/Android/obb/com.superman.plane/main.2.com.superman.plane.obbのようになります

5: AndroidManifest.xml修正

a: android:versionCode="2"にする

b: uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE"追加

7: デバイスに実行

注意：xcode ios実行したい場合はmySample2/obb-expansion-cocos2dx3.2/Resources/* Resources下のフォルダおよびファイルを元に戻す
