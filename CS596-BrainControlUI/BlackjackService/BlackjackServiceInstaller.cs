using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using System.Linq;


namespace Games.BlackjackService
{
    [RunInstaller(true)]
    public partial class BlackjackServiceInstaller : System.Configuration.Install.Installer
    {
        public BlackjackServiceInstaller()
        {
            InitializeComponent();
        }
    }
}
