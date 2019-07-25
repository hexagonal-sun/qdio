function hexStringToByte(str)
{
  if (!str) {
    return new Uint8Array();
  }

  var a = [];
  for (var i = 0, len = str.length; i < len; i+=2) {
    a.push(parseInt(str.substr(i,2),16));
  }

  return new Uint8Array(a);
}

function disableControls(state)
{
    var inputUsername = $('#inputUsername');
    var inputPassword = $('#inputPassword');
    var submitButton = $('#submitButton');
    var buttonSpinner = $('#buttonSpinner');

    inputUsername.prop('disabled', state);
    inputPassword.prop('disabled', state);
    submitButton.prop('disabled', state);
    buttonSpinner.prop('hidden', !state);
}

async function userLogin()
{
    var inputUsername = $('#inputUsername');
    var inputPassword = $('#inputPassword');
    var result;

    disableControls(true);

    try {
        result = await $.ajax({
            type: 'POST',
            url: '/userAuth/findUser',
            data: JSON.stringify({
                username: inputUsername.val()
            }),
            processData: false,
            contentType: 'application/json'
        });

        var saltByteArray = hexStringToByte(result.salt);

        var hash = keccak256.update(saltByteArray)
            .update(inputPassword.val())
            .hex()

        result = await $.ajax({
            type: 'POST',
            url: '/userAuth/userLogin',
            data: JSON.stringify({
                uid: result.user_id,
                hash: hash
            }),
            processData: false,
            contentType: 'application/json'
        });

        if (!result)
        {
            $('#alertDanger').text('Invalid username or password')
            $('#alertDanger').fadeIn()
            $('#inputUsername').focus()
            disableControls(false);
            return;
        }

        window.location.replace('/dashboard/home/');

    } catch (e) {
        $('#alertDanger').text('Failed to login: server error')
        $('#alertDanger').fadeIn()
        disableControls(false);
    }
}

$(document).ready(() => {
    $('#formSignIn').submit((e) => {
        e.preventDefault();
        $('#alertDanger').hide()
        userLogin();
    });
});
