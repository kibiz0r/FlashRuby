package
{
	import com.yeticgi.flashRuby.FlashRuby;
	import com.yeticgi.flashRuby.RubyObject;
	
	import flash.desktop.NativeProcess;
	import flash.display.Sprite;

	public class firb extends Sprite
	{
		private var flashRuby:FlashRuby;
		
		public function firb()
		{
			flashRuby = new FlashRuby();
			var fiftyFive = processInput("5 + 50");
		}
		
		public function processInput(input:String):void
		{
			var result:RubyObject = flashRuby.eval(input);
			flashRuby.stdout.puts(result);
		}
		
		public function poll():void
		{
			if (flashRuby.stdin.ready)
			{
				processInput(flashRuby.stdin.gets);
			}
		}
	}
}