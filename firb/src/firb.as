package
{
	import com.yeticgi.flashRuby.FlashRuby;
	
	import flash.desktop.NativeProcess;
	import flash.display.Sprite;
	
	public class firb extends Sprite
	{
		var flashRuby:FlashRuby;
		
		public function firb()
		{
			flashRuby = new FlashRuby();
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