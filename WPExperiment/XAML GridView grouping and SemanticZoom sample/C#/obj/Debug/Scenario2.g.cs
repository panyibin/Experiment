﻿

#pragma checksum "D:\STUDY\Git\WPExperiment\XAML GridView grouping and SemanticZoom sample\C#\Scenario2.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "E26C6E52B3CA582519ACAF3FE6D512E5"
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
    partial class Scenario2 : global::SDKTemplate.Common.LayoutAwarePage, global::Windows.UI.Xaml.Markup.IComponentConnector
    {
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 4.0.0.0")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
 
        public void Connect(int connectionId, object target)
        {
            switch(connectionId)
            {
            case 1:
                #line 43 "..\..\Scenario2.xaml"
                ((global::Windows.UI.Xaml.Controls.ListViewBase)(target)).ContainerContentChanging += this.ItemsByLetter_ContainerContentChanging;
                 #line default
                 #line hidden
                break;
            }
            this._contentLoaded = true;
        }
    }
}


