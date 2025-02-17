package imgui.test.img;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import okhttp3.*;
import java.io.IOException;
import android.app.AlertDialog;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import android.widget.Toast;


public class MainActivity2 extends Activity {
	private Button b;
	private TextView tv;
	private OkHttpClient client = new OkHttpClient();
	private String url = "http://cloudinject.com/feature/app/get/notice/ANDROID/1.0?app_id=fcb8a94120e72e2e0000242d50cf1f9f&device_code=79240bb98683e6c7&version_code=50&version_name=2.0.6&_key=59015a6dcf259361fd2d29e5ea67072e&serverNo=kCbLlpBPljHg0Ali0gjCahBy0AYSHSMB";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		tv = findViewById(R.id.activitymainTextView1);
		b = findViewById(R.id.activitymainButton1);
		Request request = new Request.Builder()
			.url(url)
			.header("User-Agent", "okhttp/3.8.0")
			.header("Connection", "close")
			.header("Accept-Encoding", "gzip")
			.header("data", "494770277a3ca672f8e22e8a45b4160f")
			.header("eagleid", "a7fa6b89-608d-42d1-a6e2-326d839a6522")	
			.build();

		client.newCall(request).enqueue(new Callback() {

				@Override
				public void onFailure(Call call, IOException iOException) {
					tv.setText("出现错误：" + iOException.getMessage());
				}

				@Override
				public void onResponse(Call call, Response response) throws IOException {
					try (Response r = response) {
						if (r.isSuccessful() && r.body() != null) {
							JsonObject jsonObject = JsonParser.parseString(r.body().string()).getAsJsonObject(); // 注意：使用 r.body().string()
							JsonObject result = jsonObject.getAsJsonObject("result");
							final String message = result.get("message").getAsString();

							runOnUiThread(new Runnable() {
									@Override
									public void run() {
										tv.setText("公告：" + message);
									}
								});
						} else {
							runOnUiThread(new Runnable() {
									@Override
									public void run() {
										tv.setText("请求时发生了错误:" + r.code());
									}
								});
						}
					} 
				}
			});
		b.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View v) {
					jumpToMainActivity2();
				}
			});
		try {
            Thread.sleep(1000); // 等待1秒，确保异步请求有足够的时间完成
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
	}
	public void jumpToMainActivity2() {
        Intent intent = new Intent(MainActivity2.this, MainActivity.class);
        startActivity(intent);
		finish();
    }
	private long firstBackTime;
	@Override
	public void onBackPressed() {
		if (System.currentTimeMillis() - firstBackTime > 2000) {
			Toast.makeText(this, "再按一次返回键退出程序", Toast.LENGTH_SHORT).show();
			firstBackTime = System.currentTimeMillis();
			return;
		}
		super.onBackPressed();
	}
}
