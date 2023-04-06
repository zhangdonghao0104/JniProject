package com.zdh.jni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.zdh.jni.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    public native void changeName();

    public native void changeAge();

    private String name = "zdh";
    private int age = 10;

    private ActivityMainBinding binding;

    public native void testArrayAction(int count, String textInfo, int[] ints, String[] strs); // String引用类型，玩数组

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());


        Log.e("TAG", "onCreate: 修改前" + name);
        changeName();
        Log.e("TAG", "onCreate: 修改后" + name);

        Log.e("TAG", "onCreate: 年龄修改前" + age);
        changeAge();
        Log.e("TAG", "onCreate: 年龄修改后" + age);
    }

    // 点击事件：操作insertObject函数
    public void test01(View view) {
        int[] ints = new int[]{1, 2, 3, 4, 5, 6};
        String[] strs = new String[]{"李小龙", "李连杰", "李元霸"};
        testArrayAction(99, "你好", ints, strs);

        for (int anInt : ints) { // Java 输出 int 数组
            Log.d("TAG", "Java test01: java ints:" + anInt);
        }

        for (String str : strs) { // 输出 String 数组
            Log.e("TAG", "Java test01: java strs:" + str);
        }
    }

    // 点击事件：操作insertObject函数
    public void test02(View view) {
    }

    // 点击事件：操作insertObject函数
    public void test03(View view) {
    }

    // 点击事件：操作insertObject函数
    public void test04(View view) {
    }

    // 点击事件：操作insertObject函数
    public void test05(View view) {
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}