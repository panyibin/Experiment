﻿

#pragma checksum "D:\STUDY\Git\WPExperiment\PhoneApp1\App8.1\PivotPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "29579687CB0DE673F6DFA2382A0E8881"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace App8._1
{
    partial class PivotPage : global::Windows.UI.Xaml.Controls.Page, global::Windows.UI.Xaml.Markup.IComponentConnector
    {
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 4.0.0.0")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
 
        public void Connect(int connectionId, object target)
        {
            switch(connectionId)
            {
            case 1:
                #line 13 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Pivot)(target)).SelectionChanged += this.Pivot_SelectionChanged;
                 #line default
                 #line hidden
                break;
            case 2:
                #line 24 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).LoadCompleted += this.Browser4_LoadCompleted;
                 #line default
                 #line hidden
                #line 24 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).ScriptNotify += this.Browser4_ScriptNotify;
                 #line default
                 #line hidden
                break;
            case 3:
                #line 21 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).LoadCompleted += this.Browser3_LoadCompleted;
                 #line default
                 #line hidden
                #line 21 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).ScriptNotify += this.Browser3_ScriptNotify;
                 #line default
                 #line hidden
                break;
            case 4:
                #line 18 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).NavigationCompleted += this.Browser2_NavigationCompleted;
                 #line default
                 #line hidden
                #line 18 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).NavigationFailed += this.Browser2_NavigationFailed;
                 #line default
                 #line hidden
                #line 18 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).LoadCompleted += this.Browser2_LoadCompleted;
                 #line default
                 #line hidden
                #line 18 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).ScriptNotify += this.Browser2_ScriptNotify;
                 #line default
                 #line hidden
                break;
            case 5:
                #line 15 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).LoadCompleted += this.Browser1_LoadCompleted;
                 #line default
                 #line hidden
                #line 15 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.WebView)(target)).ScriptNotify += this.Browser1_ScriptNotify;
                 #line default
                 #line hidden
                break;
            case 6:
                #line 39 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.homeButton_Click;
                 #line default
                 #line hidden
                break;
            case 7:
                #line 40 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.backButton_Click;
                 #line default
                 #line hidden
                break;
            case 8:
                #line 41 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.refreshButton_Click;
                 #line default
                 #line hidden
                break;
            case 9:
                #line 42 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.settingButton_Click;
                 #line default
                 #line hidden
                break;
            case 10:
                #line 43 "..\..\PivotPage.xaml"
                ((global::Windows.UI.Xaml.Controls.Primitives.ButtonBase)(target)).Click += this.navigateButton_Click;
                 #line default
                 #line hidden
                break;
            }
            this._contentLoaded = true;
        }
    }
}

