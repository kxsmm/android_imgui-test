package imgui.test.img;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity2 extends Activity {
	private Button b;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		b = findViewById(R.id.activitymainButton1);
		b.setOnClickListener(new View.OnClickListener() {

				@Override
				public void onClick(View v) {
					jumpToMainActivity2();
				}
			});
	}
    
    
	
	public void jumpToMainActivity2() {
        Intent intent = new Intent(MainActivity2.this, MainActivity.class);
        startActivity(intent);
		finish();
    }
	
}
