package com.yeticgi.flashRuby
{
	import flash.utils.Proxy;
	import flash.utils.flash_proxy;
	
	public dynamic class RubyObject extends Proxy
	{
		public function RubyObject()
		{
			
		}
		
		flash_proxy override function callProperty(name:*, ...rest):*
		{
			return null;
		}
	}
}