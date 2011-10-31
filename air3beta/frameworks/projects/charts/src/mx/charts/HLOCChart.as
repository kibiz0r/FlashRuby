////////////////////////////////////////////////////////////////////////////////
//
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2009 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////

package mx.charts
{

import mx.charts.chartClasses.CartesianChart;
import mx.charts.chartClasses.DataTip;
import mx.charts.chartClasses.DataTransform;
import mx.charts.chartClasses.Series;
import mx.charts.series.HLOCSeries;
import mx.charts.styles.HaloDefaults;
import mx.core.mx_internal;
import mx.graphics.SolidColor;
import mx.graphics.Stroke;
import mx.styles.CSSStyleDeclaration;
import mx.core.IFlexModuleFactory;

use namespace mx_internal;

//--------------------------------------
//  Styles
//--------------------------------------

/**
 *  Specifies a ratio of how wide to draw the HLOC lines
 *  relative to the horizontal axis's category widths,
 *  as a percentage in the range of 0 to 1. 
 *  A value of 1 uses the entire space, while a value of 0.6
 *  uses 60% of the category's available space.  
 *  The actual element width used is the smaller of the
 *  <code>columnWidthRatio</code> property and the
 *  <code>maxColumnWidth</code> property.
 *  Multiple element series divide this space proportionally.
 *  The default value is 0.65.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
[Style(name="columnWidthRatio", type="Number", inherit="no")]

/**
 *  Specifies how wide to draw the HLOC lines, in pixels.
 *  The actual width used is the smaller of this property
 *  and the <code>columnWidthRatio</code> property.
 *  Multiple HLOC series divide this space proportionally.
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
[Style(name="maxColumnWidth", type="Number", format="Length", inherit="no")]

//--------------------------------------
//  Other metadata
//--------------------------------------

[DefaultBindingProperty(destination="dataProvider")]

[DefaultTriggerEvent("itemClick")]

[IconFile("HLOCChart.png")]

/**
 *  The HLOCChart (High Low Open Close) control represents financial data as a series of elements
 *  representing the high, low, closing, and optionally opening values
 *  of a data series.
 *  The top and bottom of the vertical line in each element
 *  represent the high and low values for the datapoint.
 *  The right-facing tick represents the closing values,
 *  and the left tick represents the opening value if one was specified. 
 *   
 *  <p>An HLOCChart control expects its <code>series</code> property
 *  to contain an Array of HLOCSeries objects.</p>
 * 
 *  @mxml
 *  
 *  The <code>&lt;mx:HLOCChart&gt;</code> tag inherits all the properties
 *  of its parent classes and adds the following properties:</p>
 *  
 *  <pre>
 *  &lt;mx:HLOCChart
 *    <strong>Styles</strong>
 *    columnWidthRatio=".65"
 *    maxColumnWidth="<i>No default</i>"
 *  /&gt;
 *  </pre> 
 *
 *  @see mx.charts.series.HLOCSeries
 *
 *  @includeExample examples/HLOCChartExample.mxml
 *  
 *  @langversion 3.0
 *  @playerversion Flash 9
 *  @playerversion AIR 1.1
 *  @productversion Flex 3
 */
public class HLOCChart extends CartesianChart
{
    include "../core/Version.as";

    //--------------------------------------------------------------------------
    //
    //  Class initialization
    //
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //  Class constants
    //
    //--------------------------------------------------------------------------

    /**
     *  @private
     */
    private static var INVALIDATING_STYLES:Object =
    {
        columnWidthRatio: 1,
        maxColumnWidth: 1
    }

    //--------------------------------------------------------------------------
    //
    //  Constructor
    //
    //--------------------------------------------------------------------------
    
    /**
     *  Constructor.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    public function HLOCChart()
    {
        super();

        dataTipMode = "single";
    }

    //--------------------------------------------------------------------------
    //
    //  Variables
    //
    //--------------------------------------------------------------------------

    /**
     *  @private
     */
    private var _moduleFactoryInitialized:Boolean = false; 
    
    /**
     *  @private
     */
    private var _perSeriesColumnWidthRatio:Number;
    
    /**
     *  @private
     */
    private var _perSeriesMaxColumnWidth:Number;
    
    /**
     *  @private
     */
    private var _leftOffset:Number;
    
    //--------------------------------------------------------------------------
    //
    //  Overridden methods: UIComponent
    //
    //--------------------------------------------------------------------------
    
    /**
     *  @private
     */
    private function initStyles():Boolean
    {
        HaloDefaults.init(styleManager);
        
        var hlocChartStyle:CSSStyleDeclaration =
            HaloDefaults.createSelector("mx.charts.HLOCChart", styleManager);
        
        var hlocChartSeriesStyles:Array /* of Object */ = [];
        
        hlocChartStyle.defaultFactory = function():void
        {
            this.axisColor = 0xD5DEDD;
            this.chartSeriesStyles = hlocChartSeriesStyles;     
            this.columnWidthRatio = 0.65;
            this.dataTipRenderer = DataTip;
            this.fill = new SolidColor(0xFFFFFF, 0);
            this.calloutStroke = new Stroke(0x888888,2);            
            this.fontSize = 10;
            this.textAlign = "left";
            this.horizontalAxisStyleNames = ["blockCategoryAxis"];
            this.verticalAxisStyleNames = ["blockNumericAxis"];
        }
        
        var n:int = HaloDefaults.defaultColors.length;
        for (var i:int = 0; i < n; i++)
        {
            var styleName:String = "haloHLOCSeries"+i;
            hlocChartSeriesStyles[i] = styleName;
            
            var o:CSSStyleDeclaration =
                HaloDefaults.createSelector("." + styleName, styleManager);
            
            var f:Function = function(o:CSSStyleDeclaration, stroke:Stroke,
                                      tickStroke:Stroke):void
            {
                o.defaultFactory = function():void
                {
                    this.closeTickStroke = tickStroke;
                    this.openTickStroke = tickStroke;
                    this.stroke = stroke;
                    this.hlocColor = stroke.color;
                }
            }
            
            f(o, new Stroke(HaloDefaults.defaultColors[i], 0, 1),
                new Stroke(HaloDefaults.defaultColors[i], 2, 1,
                    false, "normal", "none"));
        }
        
        return true;
    }

    
    /**
     *   A module factory is used as context for using embedded fonts and for finding the style manager that controls the styles for this component.
     *  
     *  @langversion 3.0
     *  @playerversion Flash 9
     *  @playerversion AIR 1.1
     *  @productversion Flex 3
     */
    override public function set moduleFactory(factory:IFlexModuleFactory):void
    {
        super.moduleFactory = factory;
        
        if (_moduleFactoryInitialized)
            return;
        
        _moduleFactoryInitialized = true;
        
        // our style settings
        initStyles();
    }
    
    /**
     *  @private
     */
    override public function styleChanged(styleProp:String):void
    {
        if (styleProp == null || INVALIDATING_STYLES[styleProp] != undefined)
            invalidateSeries();

        super.styleChanged(styleProp);
    }

    //--------------------------------------------------------------------------
    //
    //  Overridden methods: ChartBase
    //
    //--------------------------------------------------------------------------

    /**
     *  @private
     */
    override protected function customizeSeries(seriesGlyph:Series, i:uint):void
    {
        var series:HLOCSeries = seriesGlyph as HLOCSeries;
        if (series)
        {
            if (!isNaN(_perSeriesColumnWidthRatio))
                series.columnWidthRatio = _perSeriesColumnWidthRatio;
            
            if (!isNaN(_perSeriesMaxColumnWidth))
                series.maxColumnWidth = _perSeriesMaxColumnWidth;

            series.offset = _leftOffset + i * _perSeriesColumnWidthRatio;
        }
    }
    
    /**
     *  @private
     */
    override protected function applySeriesSet(seriesSet:Array /* of Series */,
                                               transform:DataTransform):Array /* of Series */
    {
        var columnWidthRatio:Number = getStyle("columnWidthRatio");
        var maxColumnWidth:Number = getStyle("maxColumnWidth");

        _perSeriesColumnWidthRatio = columnWidthRatio / seriesSet.length;
        _perSeriesMaxColumnWidth = maxColumnWidth / seriesSet.length;
        
        _leftOffset = (1 - columnWidthRatio) / 2 +
                      _perSeriesColumnWidthRatio / 2 - 0.5;
        
        return super.applySeriesSet(seriesSet, transform);
    }
}

}
