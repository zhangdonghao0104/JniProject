package com.zdh.jni;

import android.util.Log;

public class Dog {

    // <init> 构造函数名
    public Dog() {
        Log.d("Dog", "Java Dog init...");
    }

    public Dog(int number1) {
        Log.d("Dog", "Java Dog init... number1:" + number1);
    }

    public Dog(int number1, int number2) {
        Log.d("Dog", "Java Dog init... number1:" + number1 + " number2:" + number2);
    }

    // ...

}