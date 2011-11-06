package com.yeticgi.flashRuby
{
	import com.yeticgi.nativeExtensions.FlashRubyVM;

	public class Kernel
	{
		public static function require(file:String):Object
		{
			var contents:String = File.open(file);
			return FlashRubyVM.eval(contents);
		}
	}
}