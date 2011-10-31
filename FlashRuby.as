package
{
	import flash.display.Sprite;
	import flash.external.ExtensionContext;
	import flash.filesystem.File;
	import flashruby.FlashRubyCore;
	
	public class FlashRuby extends Sprite
	{
		public function FlashRuby()
		{
			var core = new FlashRubyCore();
			var extenz:ExtensionContext = ExtensionContext.createExtensionContext("com.yeticgi.FlashRuby", "");
			extenz.call("FlashRubyInitializer");
		}
		
		/*public function Main() {
			NativeApplication.nativeApplication.addEventListener(flash.events.InvokeEvent.INVOKE, onInvoke);
		}
		
		public function onInvoke(event:InvokeEvent):void {
			var sourceFile = event.arguments[0] || "hello_world.rb";
			var sourceFileStream:FileStream = new FileStream();
			sourceFileStream.open(File.applicationDirectory.resolvePath(sourceFile), FileMode.READ);
			//var source = sourceFileStream.readUTF();
			var source = sourceFileStream.readUTFBytes(sourceFileStream.bytesAvailable);
			trace(source);
			var nativeProcess:NativeProcess = new NativeProcess();
			var nativeProcessStartupInfo:NativeProcessStartupInfo = new NativeProcessStartupInfo();
			nativeProcessStartupInfo.executable = File.applicationDirectory.resolvePath("yarv");
			nativeProcessStartupInfo.arguments.push(source);
			nativeProcess.start(nativeProcessStartupInfo);
			var output:String = nativeProcess.standardOutput.readUTFBytes(nativeProcess.standardOutput.bytesAvailable);
			trace(output);
		}*/
	}
}