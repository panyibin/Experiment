using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PhoneApp1.Resources;
using Microsoft.Phone.Tasks;
using System.Reflection;

namespace PhoneApp1
{
    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
        }

        private void Button_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {

        }

        private void SendEmail_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            EmailComposeTask emailComposeTask = new EmailComposeTask();

            string strOSVersion = null;

            strOSVersion = Environment.OSVersion.ToString();

            string appVersion = null;
            Assembly assem = Assembly.GetExecutingAssembly();

            AssemblyName assemName = assem.GetName();

            Version appVer = assemName.Version;

            emailComposeTask.Subject = "subject";
            emailComposeTask.Body = "OS version:" + strOSVersion + "\nApp version:" + appVer.ToString();
            emailComposeTask.To = "yibinpan@microsoft.com";

            emailComposeTask.Show();
        }

        private void Button_Tap_1(object sender, System.Windows.Input.GestureEventArgs e)
        {

        }

        private void SearchImage_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            WebBrowserTask wbTask = new WebBrowserTask();
            wbTask.Uri = new Uri("http://www.bing.com/images/search?q=%E4%B8%AD%E5%9B%BD%E5%9C%B0%E5%9B%BE&amp;mkt=zh-cn");

            wbTask.Show();
        }

        private void Button_Tap_2(object sender, System.Windows.Input.GestureEventArgs e)
        {

        }

        private void GoToWebBrowser_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            NavigationService.Navigate(new Uri("/WebBrowser.xaml", UriKind.Relative));
        }

        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}
    }
}