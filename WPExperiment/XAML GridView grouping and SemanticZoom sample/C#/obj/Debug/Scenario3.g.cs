﻿

#pragma checksum "D:\STUDY\Git\WPExperiment\XAML GridView grouping and SemanticZoom sample\C#\Scenario3.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "2C7C9FCA49111830F79E5573EC27DC8B"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace GroupedGridView
{
    partial class Scenario3 : global::SDKTemplate.Common.LayoutAwarePage, global::Windows.UI.Xaml.Markup.IComponentConnector
    {
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 4.0.0.0")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
 
        public void Connect(int connectionId, object target)
        {
            switch(connectionId)
            {
            case 1:
                #line 75 "..\..\Scenario3.xaml"
                ((global::Windows.UI.Xaml.Controls.ListViewBase)(target)).ContainerContentChanging += this.ItemsGridView_ContainerContentChanging;
                 #line default
                 #line hidden
                break;
            case 2:
                #line 36 "..\..\Scenario3.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.scenario3switchViewsClickHandler;
                 #line default
                 #line hidden
                break;
            }
            this._contentLoaded = true;
        }
    }
}


