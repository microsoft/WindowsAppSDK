// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace AppAttachExtension.Models
{
    public class IdentityViewModel
    {
        private string _jwtToken;
        private string _userEmail;
        private string _upn;
        private string _userName;
        private string _storageAccountConnectionString;

        public IdentityViewModel()
        {
            _jwtToken = null;
            _userEmail = null;
            _upn = null;
            _userName = null;
            _storageAccountConnectionString = null;
        }

        public string JwtToken { get => _jwtToken; set => _jwtToken = value; }
        public string UserEmail { get => _userEmail; set => _userEmail = value; }
        public string Upn { get => _upn; set => _upn = value; }
        public string UserName { get => _userName; set => _userName = value; }
        public string StorageAccountConnectionString { get => _storageAccountConnectionString; set => _storageAccountConnectionString = value; }
    }
}
