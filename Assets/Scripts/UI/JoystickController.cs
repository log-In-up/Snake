using UnityEngine.EventSystems;
using UnityEngine.UI;
using UnityEngine;
using static UnityEngine.RectTransformUtility;
using static UnityEngine.Input;

[DisallowMultipleComponent]
[RequireComponent(typeof(Image))]
public class JoystickController : MonoBehaviour, IDragHandler, IPointerDownHandler, IPointerUpHandler
{
    #region Parameters
    [SerializeField] private string horizontalAxis = "Horizontal";
    [SerializeField] private RectTransform stick = null;

    private Image joystick, joystickController;
    private Vector2 joystickBias;

    private const float zero = 0.0f, joystickMagnitude = 1.0f, joystickTransformDivisor = 2.0f;
    #endregion

    #region MonoBehaviour API
    private void Awake()
    {
        joystick = GetComponent<Image>();
        joystickController = stick.GetComponent<Image>();
    }
    #endregion

    #region Custom methods
    public void OnDrag(PointerEventData eventData)
    {
        if (ScreenPointToLocalPointInRectangle(joystick.rectTransform, eventData.position, eventData.pressEventCamera, out Vector2 position))
        {
            position.x /= joystick.rectTransform.sizeDelta.x;

            joystickBias = new Vector2(position.x, zero);
            joystickBias = (joystickBias.magnitude > joystickMagnitude) ? joystickBias.normalized : joystickBias;

            joystickController.rectTransform.anchoredPosition = new Vector2(joystickBias.x * (joystick.rectTransform.sizeDelta.x / joystickTransformDivisor), zero);
        }
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        OnDrag(eventData);
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        joystickBias = Vector2.zero;
        joystickController.rectTransform.anchoredPosition = Vector2.zero;
    }

    public float Horizontal()
    {
        return joystickBias.x != zero ? joystickBias.x : GetAxisRaw(horizontalAxis);
    }
    #endregion
}
