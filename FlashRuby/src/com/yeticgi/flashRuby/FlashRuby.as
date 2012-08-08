package com.yeticgi.flashRuby
{
	import flash.desktop.NativeApplication;
	import flash.events.InvokeEvent;
	import flash.external.ExtensionContext;
	
	public class FlashRuby
	{
		public function FlashRuby()
		{
			var extensionContext:ExtensionContext = ExtensionContext.createExtensionContext("com.yeticgi.FlashRuby", null);
			extensionContext.call("init_vm");
		}
	}
}