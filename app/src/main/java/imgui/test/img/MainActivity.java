package imgui.test.img;
 
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;
import android.app.NativeActivity;
import android.view.inputmethod.InputMethodManager;
import java.util.concurrent.LinkedBlockingQueue;
import android.view.KeyEvent;
import android.content.Context;

public class MainActivity extends NativeActivity { 
    
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //System.loadLibrary("ImGuiTest");
        //start_imgui();
        
    }
    
        // 显示软键盘
    public void showSoftInput() {
        InputMethodManager inputMethodManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.showSoftInput(this.getWindow().getDecorView(), 0);
    }

    // 隐藏软键盘
    public void hideSoftInput() {
        InputMethodManager inputMethodManager = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.hideSoftInputFromWindow(this.getWindow().getDecorView().getWindowToken(), 0);
    }

    // 队列用于从原生代码（通过 pollUnicodeChar()）轮询 Unicode 字符
    private LinkedBlockingQueue<Integer> unicodeCharacterQueue = new LinkedBlockingQueue<>();

    
    // 并且在到达这里之前没有被任何 View 消耗
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            unicodeCharacterQueue.offer(event.getUnicodeChar(event.getMetaState()));
        }
        return super.dispatchKeyEvent(event);
    }

    // 轮询 Unicode 字符
    public int pollUnicodeChar() {
        return unicodeCharacterQueue.poll() != null ? unicodeCharacterQueue.poll() : 0;
    }
    
    private native void start_imgui();
        
    
}
