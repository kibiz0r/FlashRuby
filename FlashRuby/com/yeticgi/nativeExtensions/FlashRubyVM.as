package com.yeticgi.nativeExtensions
{
	import flash.external.ExtensionContext;

	public class FlashRubyVM
	{
		public static function eval(source:String):Object
		{
			return extensionContext.call("eval", source);
		}
		
		private static var _extensionContext:ExtensionContext;
		
		public static function get extensionContext():ExtensionContext
		{
			if (_extensionContext == null)
			{
				_extensionContext = ExtensionContext.createExtensionContext("com.yeticgi.FlashRuby", null);
			}
			return _extensionContext;
		}
	}
}