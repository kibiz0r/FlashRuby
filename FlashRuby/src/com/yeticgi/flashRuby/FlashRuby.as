package com.yeticgi.flashRuby
{
	import flash.desktop.NativeApplication;
	import flash.events.InvokeEvent;
	import flash.external.ExtensionContext;
	
	public class FlashRuby
	{
		private static var extensionContext:ExtensionContext;
		
		public function FlashRuby()
		{
			extensionContext = ExtensionContext.createExtensionContext("com.yeticgi.FlashRuby", null);
			extensionContext.call("init_vm");
		}
		
		public function eval(str:String):RubyObject
		{
			return extensionContext.call("eval", str) as RubyObject;
		}
		
		public function get stdin():RubyObject
		{
			return eval("$<"); 
		}
		
		public function get stdout():RubyObject
		{
			return eval("$>");
		}
	}
}