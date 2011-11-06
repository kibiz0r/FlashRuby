package com.yeticgi.flashRuby
{
	import com.yeticgi.nativeExtensions.FlashRubyVM;
	
	import flash.desktop.NativeApplication;
	import flash.events.InvokeEvent;
	import flash.external.ExtensionContext;
	
	public class FlashRuby
	{
		public function FlashRuby()
		{
			NativeApplication.nativeApplication.addEventListener(InvokeEvent.INVOKE, onInvoke);
		}
		
		public function onInvoke(event:InvokeEvent):void {
			var input:String = event.arguments[0];
			var output:Object = Kernel.require(input);
			trace(output);
		}
	}
}