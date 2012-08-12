package
{
	import com.yeticgi.flashRuby.FlashRuby;
	import com.yeticgi.flashRuby.RubyObject;
	
	import flash.desktop.NativeProcess;
	import flash.desktop.NativeProcessStartupInfo;
	import flash.display.Sprite;
	import flash.events.NativeProcessExitEvent;
	import flash.events.ProgressEvent;
	import flash.filesystem.File;

	public class firb extends Sprite
	{
		private var flashRuby:FlashRuby;
		private var fixfb:NativeProcess;
		
		public function firb()
		{
			fixfb = new NativeProcess();
			var startup:NativeProcessStartupInfo = new NativeProcessStartupInfo();
			startup.executable = new File("/bin/sh");
			startup.arguments.push("fixfb");
			startup.workingDirectory = new File("/Users/kibiyama/git/flashruby");
			
			fixfb.addEventListener(NativeProcessExitEvent.EXIT, onFixFBDone);
			fixfb.addEventListener(ProgressEvent.STANDARD_OUTPUT_DATA, onFixFBOutput);
			fixfb.addEventListener(ProgressEvent.STANDARD_ERROR_DATA, onFixFBError);
			
			fixfb.start(startup);
		}
		
		private function onFixFBDone(event:NativeProcessExitEvent):void
		{
			flashRuby = new FlashRuby();
			var fiftyFive = processInput("5 + 50");
		}
		
		private function onFixFBOutput(event:ProgressEvent):void
		{
			var output:String = fixfb.standardOutput.readUTFBytes(fixfb.standardOutput.bytesAvailable);
		}
		
		private function onFixFBError(event:ProgressEvent):void
		{
			var error:String = fixfb.standardError.readUTFBytes(fixfb.standardError.bytesAvailable);
		}
		
		public function processInput(input:String):void
		{
			flashRuby.eval(<![CDATA[
				class FlashRubyOracle
					attr_reader :beseeched
				
					def beseech!
						@beseeched = true
					end
				
					def ask_ye?(question)
						case question
						when "Is this real life?"
							"Is this just fantasy?"
						when "Am I speaking to FlashRuby?"
							"Not quite. I am a phantom called FlashRubinius, and I will haunt this codebase until you can generate an ActionScript ByteCode representation of my compiler and execute primitive methods without my VM..."
						else
							raise "I don't understand"
						end
					end
				
					def bless_this_code
						yield "blessing"
					end
				end
				]]>.toString());
				
			var beseeched:String = <![CDATA[
				oracle = FlashRubyOracle.new
				oracle.beseech!
				
				if oracle.beseeched
					"Beseechment successful!"
				else
					"What have you done!?"
				end
				]]>.toString();
			
			var isThisFlashRuby:String = <![CDATA[
				oracle = FlashRubyOracle.new
				oracle.ask_ye? "Am I speaking to FlashRuby?"
				]]>.toString();
			
			var blessedCode:String = <![CDATA[
				oracle = FlashRubyOracle.new
				oracle.bless_this_code do |x|
					"block received #{x}"
				end
				]]>.toString();

			var beseechedResult:String = flashRuby.eval(beseeched);
			var isThisFlashRubyResult:String = flashRuby.eval(isThisFlashRuby);
			var blessedCodeResult:String = flashRuby.eval(blessedCode);
			//flashRuby.stdout.puts(result);
		}
		
		/*public function poll():void
		{
			if (flashRuby.stdin.ready)
			{
				processInput(flashRuby.stdin.gets);
			}
		}*/
	}
}